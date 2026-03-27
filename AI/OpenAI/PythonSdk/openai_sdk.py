from openai import OpenAI
from openai.types import ChatModel, Image

client = OpenAI(base_url="https://ai.dooo.ng/v1")


def greet():
    response = client.responses.create(
        model="gpt-5.2", input="你好呀，请介绍你的基本信息"
    )
    print(f"greet: {response.output_text}\n\n")


def upload_img():
    file = client.files.create(file=open("fun_img.webp", "rb"), purpose="user_data")
    response = client.responses.create(
        model="gpt-5.2",
        input=[
            {
                "role": "user",
                "content": [
                    {"type": "input_file", "file_id": file.id},
                    {
                        "type": "input_text",
                        "text": "这张图片讲了一个怎样的故事？图片部分是什么内容？",
                    },
                ],
            }
        ],
    )
    print(f"upload_img: {response.output_text}\n")


def img_url():
    response = client.responses.create(
        model="gpt-5.2",
        input=[
            {
                "role": "user",
                "content": [
                    {"type": "input_text", "text": "这是哪里？"},
                    {
                        "type": "input_image",
                        "image_url": "https://cdn.britannica.com/96/100196-050-C92064E0/Sydney-Opera-House-Port-Jackson.jpg",
                    },
                ],
            }
        ],
    )
    print(f"img_url: {response.output_text}\n")


def web_search():
    response = client.responses.create(
        model="gpt-5.2",
        tools=[{"type": "web_search"}],
        input="今天有什么重大的国际新闻？",
    )
    print(f"web_search: {response.output_text}")


def stream_response():
    pass


if __name__ == "__main__":
    # greet()
    # upload_img()
    # img_url()
    web_search()
