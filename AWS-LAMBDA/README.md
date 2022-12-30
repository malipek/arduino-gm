# AWS Lambda functions for Charts with measurements

---

Check the [architecture of the solution](https://github.com/malipek/arduino-gm/blob/master/CHARTS.md).

---

## put-records

This function is intended to be invoked by the [Serial listener](https://github.com/malipek/arduino-gm/tree/master/SERIAL-LISTENER), and writes the data received to the ``readings`` table in the AWS DynamoDB.

It must have assigned AWS IAM role with ``dynamodb:PutItem`` permission on the ``readings`` table, as well as [standard permissions for CloudWatch logs](https://docs.aws.amazon.com/lambda/latest/operatorguide/access-logs.html).

AWS IAM user configured on  [Serial listener](https://github.com/malipek/arduino-gm/tree/master/SERIAL-LISTENER) must have the ``lambda:InvokeFunction`` for the ARN of ``put-records`` function.

## get-records

This function is intended to be invoked publicly, as a webservice call.

It must have assigned AWS IAM role with ``dynamodb:Scan`` permission on the ``readings`` table, as well as [standard permissions for CloudWatch logs](https://docs.aws.amazon.com/lambda/latest/operatorguide/access-logs.html).

The function must have [Function URL](https://docs.aws.amazon.com/lambda/latest/dg/lambda-urls.html) enabled, and the [AuthType must be set to NONE](https://docs.aws.amazon.com/lambda/latest/dg/urls-auth.html).

While it's public, [CloudWatch alerts should be configured on too many invocations](https://docs.aws.amazon.com/lambda/latest/operatorguide/important-metrics.html).

The URL of the function must be hardcoded into [S3 static HTML page](https://github.com/malipek/arduino-gm/tree/master/S3).