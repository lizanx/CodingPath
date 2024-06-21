1. Are service workers asynchronous or synchronous?
> Asynchronous.

2. Can localStorage be used inside a service worker for data storage?
> No, localStorage cannot be used directly inside a service worker. Service workers operate independently and handle tasks asynchronously. For security reasons, they don’t have access to synchronous APIs like localStorage or sessionStorage. Instead, consider using IndexedDB for storage within service workers.

3. Can service workers manipulate the DOM?
> No, it's a background service.

4. Are PWAs secure?
> Yes, they force HTTPS.

5. Are PWAs platform-specific?
> No, any modern browsers that support PWA on any platform can run PWAs.

6. What are the differences between a PWA and a native app?
> PWA utilizes web UI and browser APIs, they're web apps that can run offline. 
While native apps depend on specific platforms.
