// Project UID c1f28c309e55405daf00c565d57ff9ad

#include <iostream>
#include <list>
#include <string>
using namespace std;
#include "json.hpp"
using nlohmann::json;

class OHQueue {
public:

  void push_student(json request){
    Student student;
    student.uniqname = request["uniqname"];
    student.location = request["location"];
    student.position = size() + 1;
    queue.push_back(student);
  }

  int size() const{
    return queue.size();
  }


//modifies cout
 void last_queue_position_response (json body, string http){
  string location = body["location"];
  string uniqname = body["uniqname"];
  push_student(body);
  json response = {
    {"location", location},
    {"position", size()},
    {"uniqname", uniqname}
  };

  cout << http << " 201 Created\nContent-Type: application/json; charset=utf-8\nContent-Length: " +
  to_string(response.dump().size()) + "\n\n" + response.dump();
 }
  


private:
  struct Student {
    string uniqname;
    int position;
    string location;
  };
  std::list<Student> queue;
};



int main() {
  //structure
  //define office hour queue
  //read in all the request
  //for each request, store two headers in their own strings
  //store json in temp json object
  //call helper functions on the json such as make student
  //then call function on the header to formulate json response
  OHQueue queue;
  string request;
  string temp;
  string length;
  json body;
  string http;

  while (cin >> request >> temp) {
    request = request + " " + temp;
    cin >> http;
    getline(cin, temp); // this would be "Host: localhost"
    getline(cin, temp); // this would be "Content-Type: application/json; charset=utf-8"
    getline(cin, length); 
    //potential ERROR WHEN CONTENT LENNGTH 0
    //FIND ANSWER
    cin >> body;

//potential hardcoding for HTTP/1.1
if (request == "GET /api/"){
  queue.last_queue_position_response(body, http);
}
else if (request == "GET /api/queue/"){

}
else if (request == "GET /api/queue/head/"){

}
else if (request == "POST /api/queue/tail/"){

}
else if (request == "DELETE /api/queue/head/ HTTP/1.1"){

}
else{
  //return response 400
}
}

            }
string process_request(const string& method, const string& endpoint, const json& body, OHQueue& queue) {
    if (method == "POST" && endpoint == "/api/queue/tail/") {
        queue.push_student(body);

        json response = {
            {"location", location},
            {"position", queue.size()},
            {"uniqname", uniqname},
        };

        return "HTTP/1.1 201 Created\nContent-Type: application/json; charset=utf-8\nContent-Length: " +
               to_string(response.dump().size()) + "\n\n" + response.dump();
    } else if (method == "GET" && (endpoint == "/api/queue/" || endpoint == "/api/")) {
        json response = queue.to_json();
        return "HTTP/1.1 200 OK\nContent-Type: application/json; charset=utf-8\nContent-Length: " +
               to_string(response.dump().size()) + "\n\n" + response.dump();
    } else {
        // Implement other cases, if needed
        return "";
    }
}


