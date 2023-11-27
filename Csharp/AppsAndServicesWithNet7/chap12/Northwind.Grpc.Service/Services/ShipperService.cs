using Grpc.Core; // ServerCallContext
using Packt.Shared;
using ShipperEntity = Packt.Shared.Shipper;

namespace Northwind.Grpc.Service.Services;

public class ShipperService : Shipper.ShipperBase
{
    protected readonly ILogger<ShipperService> _logger;
    protected readonly NorthwindContext db;

    public ShipperService(ILogger<ShipperService> logger,
        NorthwindContext db)
    {
        _logger = logger;
        this.db = db;
    }

    public override async Task<ShipperReply?> GetShipper(
        ShipperRequest request, ServerCallContext context)
    {
        ShipperEntity? shipper = await db.Shippers.FindAsync(request.ShipperId);

        if (shipper is null)
        {
            return null;
        }
        else
        {
            return ToShipperReply(shipper);
        }
    }

    private ShipperReply ToShipperReply(ShipperEntity shipper) =>
        new ShipperReply {
            ShipperId = shipper.ShipperId,
            CompanyName = shipper.CompanyName,
            Phone = shipper.Phone
        };
}