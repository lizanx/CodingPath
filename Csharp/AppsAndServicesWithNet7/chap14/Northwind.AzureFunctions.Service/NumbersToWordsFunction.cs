using System;
using System.IO;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Extensions.Http;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Logging;
using Newtonsoft.Json;
using System.Numerics;
using Packt.Shared;

namespace Northwind.AzureFunctions.Service
{
    public static class NumbersToWordsFunction
    {
        [FunctionName("NumbersToWordsFunction")]
        public static async Task<IActionResult> Run(
            [HttpTrigger(AuthorizationLevel.Anonymous, "get", "post", Route = null)] HttpRequest req,
            ILogger log)
        {
            log.LogInformation("C# HTTP trigger function processed a request.");

            string amount = req.Query["amount"];

            if (BigInteger.TryParse(amount, out BigInteger number))
            {
                return await Task.FromResult(new OkObjectResult(number.ToWords()));
            }
            else
            {
                return new BadRequestObjectResult($"Failed to parse: {amount}");
            }
        }
    }
}
