//#pragma optimize all

#include "/adm/simul_efun/atoi.c"
#include "/adm/simul_efun/chinese.c"
#include "/adm/simul_efun/file.c"
#include "/adm/simul_efun/gender.c"
#include "/adm/simul_efun/object.c"
#include "/adm/simul_efun/path.c"
#include "/adm/simul_efun/wizard.c"

// This must be after gender.c
#include "/adm/simul_efun/message.c"

void create()
{
	seteuid(ROOT_UID);
	write("simul_efun loaded successfully.\n");
}

string base64_encode(mixed source) {
    int count, len, a, b, c, d;
    string data, result, postfix;

    count = 0;
    len = sizeof(source);
    data = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    result = "";

    switch (len % 3) {
        case 1:
            a = source[len - 1] >> 2;
            b = (source[len - 1] & 0x03) << 4;

            postfix = sprintf("%c%c==", data[a], data[b]);
            len -= 1;
            break;
        case 2:
            a = source[len - 2] >> 2;
            b = ((source[len - 2] & 0x03) << 4) | (source[len - 1] >> 4);
            c = (source[len - 1] & 0x0f) << 2;

            postfix = sprintf("%c%c%c=", data[a], data[b], data[c]);
            len -= 2;
            break;
        default:
            postfix = "";
            break;
    }

    while (count < len) {
        a = source[count] >> 2;
        b = ((source[count] & 0x03) << 4) | (source[count + 1] >> 4);
        c = ((source[count + 1] & 0x0f) << 2) | (source[count + 2] >> 6);
        d = source[count + 2] & 0x3f;

        result += sprintf("%c%c%c%c", data[a], data[b], data[c], data[d]);
        count += 3;
    }

    return (result + postfix);
}

string query_websocket_ip(object ob) {
    if (ob && websocket(ob)) {
        object link_ob = ob->link();

        if (link_ob) {
            ob = link_ob;
        }

        return ob->query_temp("websocket/ip");
    }

    return 0;
}

string query_ip_name(object ob) {
    string ip = query_websocket_ip(ob);

    return ip ? ip : efun::query_ip_name(ob);
}

string query_ip_number(object ob) {
    string ip = query_websocket_ip(ob);

    return ip ? ip : efun::query_ip_number(ob);
}

string sha1(string text) {
    return text ? hash("sha1", text) : 0;
}

string trim(string text) {
    if (strlen(text)) {
        int code = text[0], start = 0;

        while (code == 0x20 || (0x0d >= code && code >= 0x09)) {
            ++start;
            code = text[start];
        }

        if (code) {
            int end = 1;

            code = text[<1];

            while (code == 0x20 || (0x0d >= code && code >= 0x09)) {
                ++end;
                code = text[<end];
            }

            if (start || end > 1) {
                return text[start..<end];
            }
        } else {
            return "";
        }
    }

    return text;
}
