using FluentValidation;
using MediatR;
using BlazingTrails.Shared.Features.ManageTrails.Shared;

namespace BlazingTrails.Shared.Features.ManageTrails.AddTrail;

public record AddTrailRequest(TrailDto Trail) : IRequest<AddTrailRequest.Response>
{
    public const string RouteTemplate = "/api/trail";
    
    public record Response(int TrailId);
}

public class AddTrailRequestValidator : AbstractValidator<AddTrailRequest>
{
    public AddTrailRequestValidator()
    {
        RuleFor(x => x.Trail).SetValidator(new TrailValidator());
    }
}
