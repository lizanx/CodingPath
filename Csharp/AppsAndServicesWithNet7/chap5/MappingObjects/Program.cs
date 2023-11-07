using AutoMapper;
using MappingObjects.Mappers;
using Packt.Entities;
using Packt.ViewModels;

Cart cart = new(
    Customer: new(
        FirstName: "John",
        LastName: "Smith"
    ),
    Items: new()
    {
        new(ProductName: "Apples", UnitPrice: 0.49M, Quantity: 10),
        new(ProductName: "Bananas", UnitPrice: 0.99M, Quantity: 4)
    }
);

WriteLine($"{cart.Customer}");
foreach (LineItem item in cart.Items)
{
    WriteLine($" {item}");
}

// Get the mapper configuration for converting a Cart to a Summary.
MapperConfiguration config = CartToSummaryMapper.GetMapperConfiguration();

// Create a mapper using the configuration.
IMapper mapper = config.CreateMapper();

// Perform the mapping.
Summary summary = mapper.Map<Cart, Summary>(cart);

WriteLine($"Summary: {summary.FullName} spent {summary.Total}");
