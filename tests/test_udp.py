
import subprocess
import socket
import threading

PORT = 19090
MESSAGE = "Hello from C sender!"

received = []

def receive_message():
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
        sock.bind(("127.0.0.1", PORT))
        sock.settimeout(5)

        data, address = sock.recvfrom(1024)
        received.append(data.decode())

thread = threading.Thread(target=receive_message)
thread.start()

sender = subprocess.run(
    ["./sender", "127.0.0.1", str(PORT)],
    input=MESSAGE + "\nexit\n",
    text=True,
    capture_output=True,
    timeout=10
)

thread.join(timeout=6)

assert sender.returncode == 0, sender.stderr
assert not thread.is_alive(), "Receiver timed out"
assert received == [MESSAGE], (
    f"Expected {MESSAGE!r}, got {received!r}"
)

print("PASS: C sender successfully transmitted UDP message!")
