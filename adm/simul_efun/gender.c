// gender.c

string gender_self(mixed subject)
{
	switch(objectp(subject) ? subject->query("gender") : subject) {
		case "female": return "�p";	break;
		default: return "�A";
	}
}

string gender_pronoun(string subject)
{
	switch(objectp(subject) ? subject->query("gender") : subject) {
		case "deity":	return "͢";	break;
		case "male":	return "�L";	break;
		case "female":	return "�o";	break;
		case "male-animal":
		case "female-animal":	return "�e";	break;
		default: return "��";
	}
}

