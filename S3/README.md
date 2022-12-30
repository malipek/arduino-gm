# Static S3 website with charts

---

Check the [architecture of the solution](https://github.com/malipek/arduino-gm/blob/master/CHARTS.md).

---

The site uses [Google Charts](https://developers.google.com/chart) to visualize values returned by the [get-records Lambda function](https://github.com/malipek/arduino-gm/tree/master/AWS-LAMBDA).

Change the ```https://AWS-LAMBDA/get-records.js``` to the URL of the [get-records Lambda function](https://github.com/malipek/arduino-gm/tree/master/AWS-LAMBDA).

Change the name of the file to ``index.html`` and upload it to the S3 bucket.

Enable [AWS S3 static website hosting](https://docs.aws.amazon.com/AmazonS3/latest/userguide/WebsiteHosting.html) on the bucket.