# Serial listener for system with Arduino connected

---

Check the [architecture of the solution](https://github.com/malipek/arduino-gm/blob/master/CHARTS.md).

---

[Setup credentials for the AWS IAM user](https://docs.aws.amazon.com/cli/latest/userguide/cli-configure-quickstart.html) with the permission to invoke the [put-record Lambda function](https://github.com/malipek/arduino-gm/tree/master/AWS-LAMBDA).

Connect [Arduino with GM counter](https://github.com/malipek/arduino-gm) to the serial port (USB). Check for it's name (in most cases it should be ``/dev/ttyACM0``). Change it in the source file if needed.

Launch the listener, so it's running forever, i.e. in session created with ``screen`` tool:

```
screen
python3 listener.py
Ctrl-AD
```
