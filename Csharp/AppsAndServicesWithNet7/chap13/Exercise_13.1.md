1. The underlying transports vary, WebSocket is default.(WebSocket>ServerEvent>LongPolling)
2. Single parameter and single return value, wrap needed data in a class.  
This allows additional properties to be added to the type in the future without  
breaking the contract between the client and the service.
3. Library Manager CLI tool.
4. Nothing.
5. SignalR may soon consume many resources as connections increase rapidly,  
thus it's good to separate SignalR service for easily scaling.
