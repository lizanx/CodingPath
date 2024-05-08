
namespace BlazingPizza
{
    public class Address
    {
        public int Id { get; set; }

        public string Name { get; set; } = default!;

        public string Line1 { get; set; } = default!;

        public string Line2 { get; set; } = default!;

        public string City { get; set; } = default!;

        public string Region { get; set; } = default!;

        public string PostalCode { get; set; } = default!;
    }
}
