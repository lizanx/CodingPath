using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HardwareSupplies
{
    public class HardwareItem
    {
        public long id { get; set; }
        public string name { get; set; }
        public string category { get; set; }
        public int quantity { get; set; }
        public decimal cost { get; set; }
        public decimal price { get; set; }
    }
}
