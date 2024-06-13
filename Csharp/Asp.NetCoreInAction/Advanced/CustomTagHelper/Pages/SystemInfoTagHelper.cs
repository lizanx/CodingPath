using System.Runtime.InteropServices;
using System.Text;
using System.Text.Encodings.Web;
using Microsoft.AspNetCore.Razor.TagHelpers;

namespace CustomTagHelper.Pages;

public class SystemInfoTagHelper : TagHelper
{
    [HtmlAttributeName("add-os")]
    public bool IncludeOS { get; set; }

    [HtmlAttributeName("add-machine")]
    public bool IncludeMachine { get; set; }

    private readonly HtmlEncoder _encoder;

    public SystemInfoTagHelper(HtmlEncoder encoder)
    {
        _encoder = encoder;
    }

    public override void Process(TagHelperContext context, TagHelperOutput output)
    {
        output.TagName = "div";
        output.TagMode = TagMode.StartTagAndEndTag;

        StringBuilder sb = new();

        if (IncludeOS)
        {
            sb.Append(" <strong>OS:</strong> ");
            sb.Append(_encoder.Encode(RuntimeInformation.OSDescription));
        }

        if (IncludeMachine)
        {
            sb.Append(" <strong>Machine:</strong> ");
            sb.Append(_encoder.Encode(Environment.MachineName));
        }

        output.Content.SetHtmlContent(sb.ToString());
    }
}
