
class AppConfig:
    _instance = None
    def __new__(cls):
        if cls._instance:
            return cls._instance
        cls._instance = super().__new__(cls)
        return cls._instance

if __name__ == '__main__':
    inst1 = AppConfig()
    inst2 = AppConfig()
    print(inst1 is inst2)
