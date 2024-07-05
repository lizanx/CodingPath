using Microsoft.Windows.AppNotifications;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyMediaCollection.Helpers
{
    internal class NotificationManager
    {
        private bool isRegistered;
        private Dictionary<int, Action<AppNotificationActivatedEventArgs>> notificationHandlers;

        public NotificationManager()
        {
            isRegistered = false;
            notificationHandlers = new()
            {
                { ToastWithAvatar.ScenarioId, ToastWithAvatar.NotificationReceived },
                { ToastWithText.ScenarioId, ToastWithText.NotificationReceived }
            };

        }

        ~NotificationManager()
        {
            Unregister();
        }

        public void Init()
        {
            var notificationManager = AppNotificationManager.Default;
            notificationManager.NotificationInvoked += OnNotificationInvoked;
            notificationManager.Register();
            isRegistered = true;
        }

        private void OnNotificationInvoked(AppNotificationManager sender,
            AppNotificationActivatedEventArgs notificationActivatedEventArgs)
        {
            NotificationShared.NotificationReceived();

            if (!DispatchNotification(notificationActivatedEventArgs))
            {
                NotificationShared.UnrecognizedToastOriginator();
            }
        }

        private bool DispatchNotification(AppNotificationActivatedEventArgs notificationActivatedEventArgs)
        {
            var scenarioId = notificationActivatedEventArgs.Arguments[NotificationShared.scenarioTag];

            if (scenarioId.Length != 0)
            {
                try
                {
                    notificationHandlers[int.Parse(scenarioId)](notificationActivatedEventArgs);
                    return true;
                }
                catch
                {
                    // No matched handler.
                    return false;
                }
            }
            else
            {
                // No scenario id provided.
                return false;
            }
        }

        public void ProcessLaunchActivationArgs(AppNotificationActivatedEventArgs notificationActivatedEventArgs)
        {
            DispatchNotification(notificationActivatedEventArgs);
            NotificationShared.AppLaunchedFromNotification();
        }

        public void Unregister()
        {
            if (isRegistered)
            {
                AppNotificationManager.Default.Unregister();
                isRegistered = false;
            }
        }
    }
}
