using Microsoft.AspNetCore.Razor.TagHelpers;

namespace CustomTagHelper.Pages;

[HtmlTargetElement(Attributes = "hide")]
public class HideTagHelper : TagHelper
{
    [HtmlAttributeName("hide")]
    public bool Hide { get; set; }

    public override void Process(TagHelperContext context, TagHelperOutput output)
    {
        if (Hide)
        {
            output.TagName = null;
            output.SuppressOutput();
        }
    }
}
