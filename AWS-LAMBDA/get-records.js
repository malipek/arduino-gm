const region = "eu-west-1";

const { DynamoDBClient } = require("@aws-sdk/client-dynamodb");
const { DynamoDBDocumentClient } = require("@aws-sdk/lib-dynamodb");
const { ScanCommand } = require("@aws-sdk/lib-dynamodb");

const client = new DynamoDBClient( { region: region } );
const documentClient = DynamoDBDocumentClient.from(client);

exports.handler = async () => {
    let responseBody = "";
    let statusCode = 0;

    const params = {
        TableName: "readings",
    };

    try {
        const data = await documentClient.send(new ScanCommand(params));
        return data.Items;
    } catch (err) {
        responseBody = `Unable to get readings: ${err}`;
        statusCode = 400;
        return ({responseBody,statusCode});
    }
};
