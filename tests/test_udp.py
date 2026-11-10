
import socket
import subprocess
import time

PORT = 19090
MESSAGE = b"Hello from automated test!"

receiver = subprocess.Popen(
    ["./receiver", str(PORT)],
    stdout=subprocess.PIPE,
    stderr=subprocess.PIPE,
    text=True,
    bufsize=1
)

try:
    # Wait for the receiver to start.
    ready = receiver.stdout.readline()
    listening = receiver.stdout.readline()

    assert "UDP Receiver Started" in ready
    assert f"Listening on port {PORT}" in listening

    # Send a message using a UDP socket.
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
        sock.sendto(MESSAGE, ("127.0.0.1", PORT))

    # Give the receiver time to process the message.
    time.sleep(0.5)

    receiver.terminate()
    output, errors = receiver.communicate(timeout=5)

    assert MESSAGE.decode() in output, (
        f"Message not received. Output: {output}, Errors: {errors}"
    )

    print("PASS: UDP message received successfully!")

finally:
    if receiver.poll() is None:
        receiver.kill()
        receiver.communicate()
