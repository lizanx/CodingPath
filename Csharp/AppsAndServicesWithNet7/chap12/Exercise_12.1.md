1. 
    - Protobuf binary serialization, minimizes network usage.
    - Requires HTTP/2, provides significant performance benefits.
    - Supported by almost all platforms and language.
2. A `.proto` file using gRPC syntax.
3. `DateTime`
4. To avoid blocking scenarios when server is not responding.
5. Such that clients thaht don't support RPC can use traditional HTTP calls.
