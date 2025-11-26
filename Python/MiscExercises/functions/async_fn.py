import asyncio


async def print_after_sleep(msg: str, seconds: int):
    await asyncio.sleep(seconds)
    print(msg)


async def main():
    await asyncio.gather(
        print_after_sleep("First msg", 3), print_after_sleep("Second msg", 2)
    )


if __name__ == "__main__":
    asyncio.run(main())
