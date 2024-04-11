using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.Intrinsics.X86;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Components;
using Microsoft.AspNetCore.Components.Forms;

namespace Components
{
    public class CustomCssClassProvider<ProviderType> : ComponentBase
        where ProviderType : FieldCssClassProvider, new()
    {
        [CascadingParameter]
        EditContext? CurrentEditContext {  get; set; }
        public ProviderType Provider { get; set; } = new();
        protected override void OnInitialized()
        {
            if (CurrentEditContext == null)
            {
                throw new InvalidOperationException($"{nameof(CustomCssClassProvider<ProviderType>)} requires a cascading parameter of type " +
                    $"{nameof(EditContext)}.For example, you can use{nameof(CustomCssClassProvider<ProviderType>)}inside an EditForm.");
            }

            CurrentEditContext.SetFieldCssClassProvider(Provider);
        }
    }
}
