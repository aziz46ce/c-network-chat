
import socket
import subprocess
import threading
import unittest


class UDPTests(unittest.TestCase):

    def test_receiver(self):
        message = b"Hello C receiver!"

        receiver = subprocess.Popen(
            ["./receiver", "0"],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )

        # Receiver rejects port 0, so verify validation.
        stdout, stderr = receiver.communicate(timeout=5)

        self.assertNotEqual(receiver.returncode, 0)
        self.assertIn("Invalid port number", stderr)

    def test_sender(self):
        message = "Hello from C sender!"
        received = []

        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
            sock.bind(("127.0.0.1", 0))
            sock.settimeout(5)
            port = sock.getsockname()[1]

            sender = subprocess.run(
                ["./sender", "127.0.0.1", str(port)],
                input=message + "\nexit\n",
                text=True,
                capture_output=True,
                timeout=10
            )

            data, _ = sock.recvfrom(1024)
            received.append(data.decode())

        self.assertEqual(sender.returncode, 0)
        self.assertEqual(received, [message])

    def test_invalid_sender_port(self):
        sender = subprocess.run(
            ["./sender", "127.0.0.1", "99999"],
            capture_output=True,
            text=True,
            timeout=5
        )

        self.assertNotEqual(sender.returncode, 0)
        self.assertIn("Invalid port number", sender.stderr)


if __name__ == "__main__":
    unittest.main(verbosity=2)
