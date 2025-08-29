import dotenv
import os

print("=================== os.environ ===================")
# print(f"OS environment variables: {os.environ}")
print(f"HOME: {os.getenv('HOME')}")  # returns None if key doesn't exist
print(f"HOME: {os.environ['HOME']}")  # throw if key doesn't exist
print(f"HOME: {os.environ.get('HOME')}")  # returns None if key doesn't exist

print(f"API Key: {os.environ.get('MyApiKey', "No API key found")}")
if not os.getenv("MyApiKey"):
    os.environ["MyApiKey"] = "Temporary experimental API key"  # set env vars
print(f"API Key: {os.environ['MyApiKey']}")


print("\n=================== dotenv ===================")
print(f"ENV_VAR_1: {os.getenv('ENV_VAR_1')}")
print(f"ENV_VAR_2: {os.getenv('ENV_VAR_2')}")
dotenv.load_dotenv()
print(f"ENV_VAR_1(after loading dotenv): {os.getenv('ENV_VAR_1')}")
print(f"ENV_VAR_2(after loading dotenv): {os.getenv('ENV_VAR_2')}")
