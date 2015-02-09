var release = false;

function var_dump(e)
{
    if (release == false)
	console.log(JSON.stringify(e));
}

function http_request(url, async)
{
    var req = new XMLHttpRequest();

    req.open('GET', url, async);
    req.send(null);
    return (req.responseText);
}

function appMessageUpdate(e)
{
    http_request("http://dragonstorm.fr/games/wohrrrrld-breaker/connect.php");
}

Pebble.addEventListener("appmessage", appMessageUpdate);
