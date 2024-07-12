using UnoMediaCollection.Enums;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UnoMediaCollection.Models
{
    public class Medium
    {
        public int Id { get; set; }

        public string? Name { get; set; }

        public ItemType MediaType { get; set; }
    }
}
