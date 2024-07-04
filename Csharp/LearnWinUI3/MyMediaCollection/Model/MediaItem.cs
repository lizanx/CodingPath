using Dapper.Contrib.Extensions;
using MyMediaCollection.Enums;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyMediaCollection.Model
{
    public class MediaItem
    {
        [Key]
        public int Id { get; set; }

        public string Name { get; set; }

        public ItemType MediaType { get; set; }

        [Computed]
        public Medium MediumInfo { get; set; }

        public int MediumId => MediumInfo.Id;

        public LocationType Location {  get; set; }
    }
}
