using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel.DataAnnotations;

namespace Data.Models
{
    public class Category
    {
        public string? Id { get; set; }
        [Required]
        public string Name { get; set; } = string.Empty;
    }
}
