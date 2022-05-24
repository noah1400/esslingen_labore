
#include <string>
#include <iostream>

// Implementierung

using namespace std;

class AuthenticationResult {
    bool authenticated;
    string username;
    public:
        AuthenticationResult(bool authenticated, string username);
        bool isAuthenticated();
        string getUsername();
        void setAuthenticated(bool authenticated);
        void setUsername(string username);
};

AuthenticationResult::AuthenticationResult(bool authenticated, string username = "unauthenticated_user")
    : authenticated(authenticated), username(username) {}
bool AuthenticationResult::isAuthenticated() {
    return authenticated;
}
string AuthenticationResult::getUsername() {
    return username;
}
void AuthenticationResult::setAuthenticated(bool authenticated) {
    this->authenticated = authenticated;
}
void AuthenticationResult::setUsername(string username) {
    this->username = username;
}





class IAuthentification {
    public:
        virtual AuthenticationResult authenticate() = 0;
};





class Client {
    IAuthentification* auth = nullptr;
    AuthenticationResult authResult = AuthenticationResult(false, "unauthenticated_user");
    public:
        void setAuthentication(IAuthentification* auth);
        void execute();
};

void Client::setAuthentication(IAuthentification* auth) {
    this->auth = auth;
}

void Client::execute(){
    authResult = auth->authenticate();
    if (authResult.isAuthenticated()) {
        cout << "Das Programm wird ausgeführt für " << authResult.getUsername() << "." << endl;
    } else {
        cout << "Das Programm konnte nicht ausgeführt werden." << endl;
    }
}





class MockAuth : public IAuthentification {
    public:
        AuthenticationResult authenticate();
};

AuthenticationResult MockAuth::authenticate() {
    return AuthenticationResult(true, "Default");
}





class UsernamePassword : public IAuthentification {
    public:
        AuthenticationResult authenticate();
};

AuthenticationResult UsernamePassword::authenticate(){
    string username;
    string password;
    cout << "Username: " << endl;
    cin >> username;
    cout << "Password: " << endl;
    cin >> password;
    if ( username == password ){
        return AuthenticationResult(true, username);
    }else{
        return AuthenticationResult(false, username);
    }
}





class Certificate : public IAuthentification {
    public:
        AuthenticationResult authenticate();
};

AuthenticationResult Certificate::authenticate(){
    string certOwner;
    cout << "Zertifikatsaussteller: " << endl;
    cin >> certOwner;
    if ( certOwner == "hs-esslingen" ){
        return AuthenticationResult(true, "certificate.owner");
    } else {
        return AuthenticationResult(false);
    }
}


int main(int argc, char* argv[]) {
    Client client;

    cout << "Authentifizierung über MockAuth" << endl;
    IAuthentification* mockauth = new MockAuth();
    client.setAuthentication(mockauth);
    client.execute();

    cout << "Authentifizierung über UsernamePassword" << endl;
    IAuthentification* usernamepassword = new UsernamePassword();
    client.setAuthentication(usernamepassword);
    client.execute();

    cout << "Authentifizierung über Zertifikat" << endl;
    IAuthentification* certificate = new Certificate();
    client.setAuthentication(certificate);
    client.execute();
    return 0;
}

