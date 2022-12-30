const region = "eu-west-1";
const expiry = 30 * 24 * 3600; //month

const { DynamoDBClient } = require("@aws-sdk/client-dynamodb");
const { DynamoDBDocumentClient } = require("@aws-sdk/lib-dynamodb");
const { PutCommand } = require("@aws-sdk/lib-dynamodb");

const client = new DynamoDBClient( { region: region } );
const documentClient = DynamoDBDocumentClient.from(client);

exports.handler = async (event) => {
    let responseBody = "";
    let statusCode = 0;
    let record = event;
    record.timestamp = Math.floor(Date.now()/1000);
    record.exp = record.timestamp + expiry;

    const params = {
        TableName: "readings",
        Item: record
    };

    try {
        const data = await documentClient.send(new PutCommand(params));
        responseBody = JSON.stringify(data);
        statusCode = 201;
    } catch (err) {
        responseBody = `Unable to put readings: ${err}`;
        statusCode = 400;
    }
    return ({responseBody,statusCode});
};
