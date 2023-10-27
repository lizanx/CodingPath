using Microsoft.Azure.Cosmos;

using System.Net; // HttpStatusCode

partial class Program
{
    private static string endpointUri = "https://localhost:8081/";
    private static string primaryKey = "C2y6yDjf5/R+ob0N8A7Cgv30VRDJIWEHLM+4QDU5DE2nQ9nDuVTqobD4b8mGGyPMbIZnqyMsEcaGQy67XIw/Jw==";

    static async Task CreateCosmosResources()
    {
        SectionTitle("Creating Cosmos Resources");

        try
        {
            using (CosmosClient client = new(accountEndpoint: endpointUri, authKeyOrResourceToken: primaryKey))
            {
                DatabaseResponse dbResponse = await client.CreateDatabaseIfNotExistsAsync("Northwind", throughput: 400);
                string status = dbResponse.StatusCode switch
                {
                    HttpStatusCode.OK => "exists",
                    HttpStatusCode.Created => "created",
                    _ => "unknown",
                };
                WriteLine($"Database ID: {dbResponse.Database.Id}, Status: {status}");

                IndexingPolicy indexingPolicy = new()
                {
                    IndexingMode = IndexingMode.Consistent,
                    Automatic = true,
                    IncludedPaths = { new IncludedPath { Path = "/"} },
                };

                ContainerProperties containerProperties = new("Products", partitionKeyPath: "/productId")
                {
                    IndexingPolicy = indexingPolicy
                };

                ContainerResponse containerResponse = await dbResponse.Database.CreateContainerIfNotExistsAsync(
                    containerProperties: containerProperties,
                    throughput: 1000);
                status = containerResponse.StatusCode switch
                {
                    HttpStatusCode.OK => "exists",
                    HttpStatusCode.Created => "created",
                    _ => "unknown",
                };
                WriteLine($"Container ID: {containerResponse.Container.Id}, Status: {status}");

                Container container = containerResponse.Container;
                ContainerProperties properties = await container.ReadContainerAsync();

                WriteLine($"\tPartitionKeyPath: {properties.PartitionKeyPath}");
                WriteLine($"\tLastModified: {properties.LastModified}");
                WriteLine($"\tIndexingPolicy.IndexingMode: {properties.IndexingPolicy.IndexingMode}");
                WriteLine($"\tIndexingPolicy.IncludedPaths: {properties.IndexingPolicy.IncludedPaths}");
                WriteLine($"\tIndexingPolicy: {properties.IndexingPolicy}");
            }
        }
        catch (HttpRequestException ex)
        {
            WriteLine($"Error: {ex.Message}");
            WriteLine("Hint: Make sure the Azure Cosmos Emulator is running.");
        }
        catch (Exception ex)
        {
            WriteLine($"Error: {ex.GetType()} says {ex.Message}");
        }
    }
}