using Microsoft.AspNetCore.Razor.TagHelpers;

namespace CustomTagHelper.Pages;

public class MarkdownTagHelper : TagHelper
{
    public override async Task ProcessAsync(TagHelperContext context, TagHelperOutput output)
    {
        var markdownRazorContent = await output.GetChildContentAsync();
        string markdown = markdownRazorContent.GetContent();

        string markdownHtml = Markdig.Markdown.ToHtml(markdown);

        output.Content.SetHtmlContent(markdownHtml);
        output.TagName = null;
    }
}
