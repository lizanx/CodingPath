1. HTTP/HTTPS
2. It exposes CRUD methods directly to user, not confined to the methods exposed by WebApi only.
3. Decorate the method with `[EnableQuery]`.
4. /ordersystem/customers  
  ?\$select=CustomerId,CompanyName,City,Country  
  &$filter=(Country eq 'Germany') and (Orders/$count gt 1)  
5. Use `$expand` to specify the name of the navigation property.