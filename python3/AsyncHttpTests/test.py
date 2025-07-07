import aiohttp
import asyncio
import aiounittest
import unittest


class HttpPinger :
    session : aiohttp.ClientSession

    def __init__(self) -> None:
        pass

    async def create_new_session(self) :
        self.session = aiohttp.ClientSession()


    async def ping(self) :
        url = "http://www.google.com"
        return await self.session.get(url)

    async def close(self) :
        await self.session.close()

class Test(unittest.IsolatedAsyncioTestCase) :
    pinger : HttpPinger

    def __init__(self, methodName: str = ...) -> None:
        super().__init__(methodName)
        self.pinger = HttpPinger()

    async def asyncSetUp(self) -> None:
        await self.pinger.create_new_session()


    async def asyncTearDown(self) -> None:
        await self.pinger.close()

    async def test_pinger(self) :
        result = await self.pinger.ping()
        print(result)

if __name__ == "__main__" :
    unittest.main()

