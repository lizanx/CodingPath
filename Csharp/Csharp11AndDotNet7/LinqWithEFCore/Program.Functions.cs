using System.Xml.Linq;
using System.Xml;
using Packt.Shared;

partial class Program
{
    static void FilterAndSort(decimal maxUnitPrice)
    {
        SectionTitle($"Filter all products with unit price less than {maxUnitPrice} and sort them.");

        using (Northwind db = new())
        {
            var products = db.Products
                .Where( p => (p.UnitPrice ?? 0M) <= maxUnitPrice )
                .OrderBy( p => (p.UnitPrice ?? 0M) )
                .ThenBy( p => p.ProductName );
            
            if (products is null || !products.Any())
            {
                WriteLine("No products found.");
                return;
            }

            WriteLine($"{"Product Name", -40}\t|\tProduct Unit Price");
            foreach (Product p in products)
            {
                WriteLine($"{p.ProductName, -40}\t|\t{p.UnitPrice}");
            }
        }
    }
    static void OutputProductsAsXml()
    {
        SectionTitle("Output products as XML");

        using (Northwind db = new())
        {
            Product[] products = db.Products.ToArray();

            XElement xml = new("products",
                from p in products
                select new XElement(
                    "product",
                    new XAttribute("id", p.ProductId),
                    new XAttribute("price", p.UnitPrice ?? 0M),
                    new XElement("name", p.ProductName)
                )
            );

            using (XmlWriter xmlWriter =
                XmlWriter.Create(
                    File.Create(Path.Combine(Environment.CurrentDirectory, "products.xml")),
                    new XmlWriterSettings() { Indent = true }
                )
            )
            {
                xml.WriteTo(xmlWriter);
            }
        }
    }
}