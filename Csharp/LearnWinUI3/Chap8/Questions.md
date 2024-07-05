1. What type of Windows notification can be used to initiate a data sync from the cloud?
> Cloud-based notifications using Azure and Windows Push Notification Service.

2. Which type of notification doesn’t rely on WNS?
> Local app notifications.

3. Where do you register your app before configuring notification services in Azure?
> Microsoft Store.

4. Which Windows App SDK namespace contains the objects for working with app notifications?
> `Microsoft.Windows.AppNotifications`

5. Which class has methods to register and unregister your app for handling app notifications?
> `AppNotificationManager`

6. Which property can be set if you would like notifications from your app to disappear after a system reboot?
> By default app notifications are not persisted. If they re-appear after boot,
> it's because the app starts on system boot and re-creates the notifications.

7. Can notifications from WNS prompt the user with a toast notification?
> Yes.
