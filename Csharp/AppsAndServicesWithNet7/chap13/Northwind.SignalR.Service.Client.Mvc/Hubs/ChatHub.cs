using Microsoft.AspNetCore.SignalR;
using Northwind.Chat.Models;

namespace Northwind.SignalR.Service.Hubs;

public class ChatHub : Hub
{
    // a new instance of ChatHub is created to process each method so
    // we must store user names, connection IDs, and groups in a static field
    private static Dictionary<string, UserModel> Users = new();

    public async Task Register(UserModel newUser)
    {
        UserModel user;
        string action = "registered as a new user";

        if (Users.ContainsKey(newUser.Name))
        {
            user = Users[newUser.Name];

            if (user.Groups is not null)
            {
                foreach (string group in user.Groups.Split(','))
                {
                    await Groups.RemoveFromGroupAsync(user.ConnectionId, group);
                }
            }
            user.Groups = newUser.Groups;
            // ConnectionId might have changed if the browser refreshed,
            // so update it.
            user.ConnectionId = newUser.ConnectionId;

            action = "updated your registered user";
        }
        else
        {
            if (string.IsNullOrEmpty(newUser.Name))
            {
                newUser.Name = Guid.NewGuid().ToString();
            }
            newUser.ConnectionId = Context.ConnectionId;
            Users.Add(newUser.Name, newUser);
            user = newUser;
        }

        if (user.Groups is not null)
        {
            // A user doesn't have to belong to any groups,
            // but if it does, then register them with the hub.
            foreach (string group in user.Groups.Split(','))
            {
                await Groups.AddToGroupAsync(user.ConnectionId, group);
            }
        }

        // Send a messagge to the registering user informing success.
        MessageModel message = new()
        {
            From = "SignalR Hub",
            To = user.Name,
            Body = $"You have successfully {action} with connection ID {user.ConnectionId}"
        };
        IClientProxy proxy = Clients.Client(user.ConnectionId);
        await proxy.SendAsync("ReceiveMessage", message);
    }

    public async Task SendMessage(MessageModel message)
    {
        IClientProxy proxy;

        if (string.IsNullOrEmpty(message.To))
        {
            message.To = "EveryOne";
            proxy = Clients.All;
            await proxy.SendAsync("ReceiveMessage", message);
            return;
        }

        // If To has a value, then split it into a list of user and group names.
        string[] userAndGroupList = message.To.Split(',');
        foreach (string userOrGroup in userAndGroupList)
        {
            if (Users.ContainsKey(userOrGroup))
            {
                message.To = $"User: {Users[userOrGroup].Name}";
                proxy = Clients.Client(Users[userOrGroup].ConnectionId);
            }
            else
            {
                message.To = $"Group: {userOrGroup}";
                proxy = Clients.Group(userOrGroup);
            }
            
            await proxy.SendAsync("ReceiveMessage", message);
        }
    }
}