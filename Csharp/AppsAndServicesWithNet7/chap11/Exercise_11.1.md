1. It's not protocol dependent, many protocols can be used(http/tcp/websocket...).
2. GraphQL query doducment: "application/graphql".
3. Prefix the pamameter with `$`.
4. Strawberry Shake includes a tool to generate strongly typed proxies that call a GraphQL service  
and can be more easily used by a .NET client, instead of manually making requests to the service.
5. Use a mutation request with proper `Product` data.
