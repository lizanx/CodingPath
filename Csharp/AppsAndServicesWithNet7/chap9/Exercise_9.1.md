1. GET/POST/PUT/DELETE/HEAD/PATCH, TRACE/OPTIONS/CONNECT
2. 
    - 200: OK
    - 201: Created
    - 204: No content
    - 400: Bad request
    - 404: Not found
    - 401: Unauthorized
    - 403: Forbidden
    - 500: Internal server error
3. An ASP.NET Core Web APIs service requires a controller class to define the endpoints.  
An ASP.NET Core Minimal APIs service does not need a controller.  
A Minimal APIs service can therefore be simpler, and implemented in fewer statements, hence the name.
4. `app.MapPut("api/customers", () => {})`
5. Use attributes: `[FromRoute]` / `[FromQuery]` / `[FromBody]`
6. No, enabling CORS deliberate weakens security for web services, as it relaxes the same origin policy  
of browser. It has no effect on non-browser clients.
7. The service is injected in DI, but maybe you forget to add the middleware.  
Remember to add `app.UserHttpLogging` after building and before running.  
Or maybe the logging level is too high(Warning/Error), set the level to Information in app.settings.
8. Define rate limit options in app.settings, inject the service, seed the service, and add the middleware.
9. Use the extension method `RouteHandlerBuilder.RequireRateLimiting(string policyName)` for the endpoint.
10. JWT: json web tokens, used for authorization.
