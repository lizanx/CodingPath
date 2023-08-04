using Microsoft.EntityFrameworkCore;
using Packt.Shared;

// Northwind db = new();
// WriteLine($"Provider: {db.Database.ProviderName}");

// QueryingCategories();
// FilteredIncludes();
// QueryingProducts();
// QueryingWithLike();
// GetRandomProduct();

// var resultAdd = AddProduct(categoryId: 6,
//     productName: "Bob's Burgers", price: 500M);
// if (resultAdd.affected == 1)
// {
//     WriteLine($"Add product successful with ID: {resultAdd.productId}");
// }
// ListProducts(new int[] { resultAdd.productId });

// var resultUpdate = IncreaseProductPrice("Bob", 20M);
// if (resultUpdate.affected == 1)
// {
//     WriteLine($"Increase price success for ID: {resultUpdate.productId}.");
// }
// ListProducts( new int[] { resultUpdate.productId });

AddProduct(categoryId: 6,
    productName: "Bob's Burgers", price: 500M);
AddProduct(categoryId: 6,
    productName: "Bob's Burgers-2", price: 500M);
AddProduct(categoryId: 6,
    productName: "Bob's Burgers-3", price: 500M);
WriteLine("About to delete all products whose name starts with Bob.");
Write("Press Enter to continue or any other key to exit: ");
if (ReadKey(intercept: true).Key == ConsoleKey.Enter)
{
    int deleted = DeleteProducts(productNameStartsWith: "Bob");
    WriteLine($"{deleted} product(s) were deleted.");
}
else
{
    WriteLine("Delete was canceled.");
}
