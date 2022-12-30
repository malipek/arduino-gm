# Charts for Arduino GM project

## Idea

Visual presentation of measurements made with [ARDUINO-GM](https://github.com/malipek/arduino-gm/blob/master/README.md) project is possible by utilizing serial data, and Internet accessible database.

## Solution

Use AWS Lambda and DynamoDB to store readings. Automatic measurement expiry may be used thanks to [TTL functionality](https://docs.aws.amazon.com/amazondynamodb/latest/developerguide/TTL.html).

Charts HTML site can be hosted on S3 with the [AWS S3 static website hosting](https://docs.aws.amazon.com/AmazonS3/latest/userguide/WebsiteHosting.html).

Reading data from DynamoDB table can be achieved with [AWS Lambda with public Function URL](https://docs.aws.amazon.com/lambda/latest/dg/lambda-urls.html).

![Draw.io schema of the infrastructure for Charts](https://github.com/malipek/arduino-gm/blob/master/media/drawio-arduino-gm.png?raw=true)

![Screenshot of website with charts for measurements](https://github.com/malipek/arduino-gm/blob/master/media/google_chart_screenshoot.png?raw=true)

### Components used

* [Serial listener for system with Arduino connected](https://github.com/malipek/arduino-gm/tree/master/SERIAL-LISTENER)
* [AWS Lambda functions](https://github.com/malipek/arduino-gm/tree/master/AWS-LAMBDA)
* [Google Charts on S3 Static HTML site](https://github.com/malipek/arduino-gm/tree/master/S3)

s
## Security consideration

Due to possible ["Denial of Wallet attacks"](https://www.sciencedirect.com/science/article/pii/S221421262100079X), it's recommended to disable on-demand scaling for DynamoDB and limit provisioned capacity to the lowest possible numbers. Alerting on request throttling should be [enabled in CloudWatch](https://docs.aws.amazon.com/amazondynamodb/latest/developerguide/creating-alarms.html).

Lambda functions have default limit of 1000 concurrent calls. [CloudWatch alerts should be configured on too many invocations](https://docs.aws.amazon.com/lambda/latest/operatorguide/important-metrics.html).
