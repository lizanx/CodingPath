import asyncio

async def greet(name: str):
    await asyncio.sleep(len(name))
    return f"Hello, {name}"

async def main():
    tasks = [greet(name) for name in ("Gavin", "Christine", "Mary")]
    results = await asyncio.gather(*tasks)
    for greeting in results:
        print(greeting)

asyncio.run(main())
