using Microsoft.Azure.Cosmos;
using Microsoft.EntityFrameworkCore;
using Packt.Shared;
using Northwind.CosmosDb.Items;

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
                    IncludedPaths = { new IncludedPath { Path = "/" } },
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

    static async Task CreateProductItems()
    {
        SectionTitle("Creating Product Items");

        double totalCharge = 0.0;

        try
        {
            using (CosmosClient client = new(accountEndpoint: endpointUri, authKeyOrResourceToken: primaryKey))
            {
                Container container = client.GetContainer(databaseId: "Northwind", containerId: "Products");

                using (NorthwindContext db = new())
                {
                    ProductCosmos[] products = db.Products
                        .Include(p => p.Category)
                        .Include(p => p.Supplier)
                        .Where(p => p.Category != null && p.Supplier != null)
                        .Select(p => new ProductCosmos
                        {
                            id = p.ProductId.ToString(),
                            productId = p.ProductId.ToString(),
                            productName = p.ProductName,
                            quantityPerUnit = p.QuantityPerUnit,
                            category = new CategoryCosmos
                            {
                                categoryId = p.Category!.CategoryId,
                                categoryName = p.Category.CategoryName,
                                description = p.Category.Description,
                            },
                            supplier = new SupplierCosmos
                            {
                                supplierId = p.Supplier!.SupplierId,
                                companyName = p.Supplier.CompanyName,
                                contactName = p.Supplier.ContactName,
                                contactTitle = p.Supplier.ContactTitle,
                                address = p.Supplier.Address,
                                city = p.Supplier.City,
                                country = p.Supplier.Country,
                                postalCode = p.Supplier.PostalCode,
                                region = p.Supplier.Region,
                                phone = p.Supplier.Phone,
                                fax = p.Supplier.Fax,
                                homePage = p.Supplier.HomePage
                            },
                            unitPrice = p.UnitPrice,
                            unitsInStock = p.UnitsInStock,
                            reorderLevel = p.ReorderLevel,
                            unitsOnOrder = p.UnitsOnOrder,
                            discontinued = p.Discontinued,
                        })
                        .ToArray();

                    foreach (ProductCosmos product in products)
                    {
                        try
                        {
                            ItemResponse<ProductCosmos> productResponse =
                                await container.ReadItemAsync<ProductCosmos>(id: product.id, new PartitionKey(product.productId));
                            WriteLine($"Item with Id: {productResponse.Resource.id} exists. Query consumed {productResponse.RequestCharge} RUs.");
                            totalCharge += productResponse.RequestCharge;
                        }
                        catch (CosmosException ex) when (ex.StatusCode == HttpStatusCode.NotFound)
                        {
                            ItemResponse<ProductCosmos> productResponse =
                                await container.CreateItemAsync(product);

                            WriteLine("Created item with id: {0}. Insert consumed {1} RUs.",
                                productResponse.Resource.id, productResponse.RequestCharge);
                            totalCharge += productResponse.RequestCharge;
                        }
                        catch (Exception ex)
                        {
                            WriteLine($"Error {ex.GetType()} says {ex.Message}");
                        }
                    }
                }
            }
        }
        catch (HttpRequestException ex)
        {
            WriteLine($"Error: {ex.Message}");
            WriteLine("Hint: Make sure the Azure Cosmos Emulator is running.");
        }
        catch (Exception ex)
        {
            WriteLine($"Error {ex.GetType()} says {ex.Message}");
        }

        WriteLine("Total requests charge: {0:N2} RUs", totalCharge);
    }

    static async Task ListProductItems(string sqlText = "SELECT * FROM c")
    {
        SectionTitle("List Product Items");

        try
        {
            using (CosmosClient client = new(accountEndpoint: endpointUri, authKeyOrResourceToken: primaryKey))
            {
                Container container = client.GetContainer(databaseId: "Northwind", containerId: "Products");

                WriteLine($"Running query: {sqlText}");

                QueryDefinition query = new(sqlText);

                using FeedIterator<ProductCosmos> resultIterator =
                    container.GetItemQueryIterator<ProductCosmos>(query);
                if (!resultIterator.HasMoreResults)
                {
                    WriteLine("No results found.");
                }
                while (resultIterator.HasMoreResults)
                {
                    FeedResponse<ProductCosmos> products =
                        await resultIterator.ReadNextAsync();

                    WriteLine("Status code: {0}, Request charge: {1} RUs",
                        products.StatusCode, products.RequestCharge);

                    WriteLine("{0} products found.", products.Count);

                    foreach (ProductCosmos product in products)
                    {
                        WriteLine("id: {0}, productName: {1}, unitPrice: {2}",
                            product.id, product.productName, product.unitPrice);
                    }
                }
            }
        }
        catch (HttpRequestException ex)
        {
            WriteLine("Error: {0}", arg0: ex.Message);
            WriteLine("Hint: Make sure the Azure Cosmos Emulator is running.");
        }
        catch (Exception ex)
        {
            WriteLine("Error: {0} says {1}",
                arg0: ex.GetType(), arg1: ex.Message);
        }
    }

    static async Task DeleteProductItems()
    {
        SectionTitle("Delete Product Items");

        double totalCharge = 0.0;

        try
        {
            using CosmosClient client = new(accountEndpoint: endpointUri, authKeyOrResourceToken: primaryKey);
            Container container = client.GetContainer(databaseId: "Northwind", containerId: "Products");

            string sqlText = "SELECT * FROM c";
            WriteLine($"Running query: {sqlText}");

            QueryDefinition query = new(sqlText);

            using FeedIterator<ProductCosmos> resultIterator =
                container.GetItemQueryIterator<ProductCosmos>(query);

            while (resultIterator.HasMoreResults)
            {
                FeedResponse<ProductCosmos> products =
                    await resultIterator.ReadNextAsync();

                foreach (ProductCosmos product in products)
                {
                    WriteLine("Delete id: {0}, productName: {1}",
                        product.id, product.productName);

                    ItemResponse<ProductCosmos> response =
                        await container.DeleteItemAsync<ProductCosmos>(
                            id: product.id, partitionKey: new PartitionKey(product.id));

                    WriteLine("Status code: {0}, Request charge: {1} RUs.",
                        response.StatusCode, response.RequestCharge);

                    totalCharge += response.RequestCharge;
                }
            }
        }
        catch (HttpRequestException ex)
        {
            WriteLine("Error: {0}", arg0: ex.Message);
            WriteLine("Hint: Make sure the Azure Cosmos Emulator is running.");
        }
        catch (Exception ex)
        {
            WriteLine("Error: {0} says {1}",
            arg0: ex.GetType(),
            arg1: ex.Message);
        }

        WriteLine("Total requests charge: {0:N2} RUs", totalCharge);
    }
}