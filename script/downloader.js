function download_filecxx(url)
{
    var blobObject = new Blob(["I scream. You scream. We all scream for ice cream."]);

    window.navigator.msSaveBlob(blobObject, 'msSaveBlob_testFile.txt'); // The user only has the option of clicking the Save button.
    alert('File save request made using msSaveBlob() - note the single "Save" button below.');

    var fileData = ["Before you insult a person, walk a mile in their shoes. That way, when you insult them, you'll be a mile away - and have their shoes."];
    blobObject = new Blob(fileData);
    window.navigator.msSaveOrOpenBlob(blobObject, 'msSaveBlobOrOpenBlob_testFile.txt'); // Now the user will have the option of clicking the Save button and the Open button.
    alert('File save request made using msSaveOrOpenBlob() - note the two "Open" and "Save" buttons below.');
}
