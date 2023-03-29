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
 void last_queue_position_response (json body){
  string location = body["location"];
  string uniqname = body["uniqname"];
  push_student(body);
  json response = {
    {"location", location},
    {"position", size()},
    {"uniqname", uniqname}
  };
  string response_string = response.dump(4) + "\n";
  string content_length = to_string(response_string.length());
  cout << "HTTP/1.1 201 Created\n"
  << "Content-Type: application/json; charset=utf-8\nContent-Length: "
   << content_length << "\n\n" << response_string;
 }

//GET /api/
 void read_routes (){
    //response is always the same for this route
    json response =  {
        {"queue_head_url", "http://localhost/queue/head/"},
        {"queue_list_url", "http://localhost/queue/"},
        {"queue_tail_url", "http://localhost/queue/tail/"}
 };
  string response_string = response.dump(4) + "\n";
  string content_length = to_string(response_string.length());
 //could have formatting issues with \n
    cout << "HTTP/1.1 200 OK\n" << 
    "Content-Type: application/json; charset=utf-8\nContent-Length: " 
    << content_length << "\n\n" << response_string;
 }
  

  void read_all_queue_positions(){
    //convert queue to JSON object in correct format
    //JSON object will have format: count - array len
    //results - an array of students in the queue in JSON format
    //convert to string with dump
    //get length using .length
    //cout all the shit above
    json output;
    json response = {
      {"count", size()}
    };
    json temp;
    for (auto it:queue){
      temp["location"] = it.location;
      temp["position"] = it.position;
      temp["uniqname"] = it.uniqname;  
      output.push_back(temp);
    }
    response["results"] = output;
    string body = response.dump(4) + "\n";
    cout << 
    "HTTP/1.1 200 OK\nContent-Type: application/json; charset=utf-8\nContent-Length: "
    << body.length() << endl << endl << body;
  }

  void read_first_queue_position(){
    json output;
    output["location"] = queue.begin()->location;
    output["position"] = queue.begin()->position;
    output["uniqname"] = queue.begin()->uniqname;
    //is this correct usage of dump 
    string body = output.dump(4) + "\n";
    cout << 
    "HTTP/1.1 200 OK\nContent-Type: application/json; charset=utf-8\nContent-Length: "
    << body.length() << endl << endl << body;
  }

  //delete endpoint
  //modifies: queue, cout
  void delete_request(){
    queue.pop_front();
    //decrement positions by 1
    for (auto it:queue){
      it.position -= 1;
    }
    cout << "HTTP/1.1 204 No Content" << endl << 
            "Content-Type: application/json; charset=utf-8" << endl <<
            "Content-Length: 0" << "\n\n";
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
  while (cin >> request >> temp) {
    request = request + " " + temp;
    getline(cin, temp); // this would be HTTP/1.1
    getline(cin, temp); // this would be "Host: localhost"
    getline(cin, temp); // this would be "Content-Type: application/json; charset=utf-8"
    getline(cin, length);

    if (length != "Content-Length: 0"){
      cin >> body;
    }

      

    if (request == "GET /api/"){
      queue.read_routes();
    }
    else if (request == "GET /api/queue/"){
      queue.read_all_queue_positions();
    }
    else if (request == "GET /api/queue/head/"){
      queue.read_first_queue_position();
    }
    else if (request == "POST /api/queue/tail/"){
      queue.last_queue_position_response(body);
    }

    else if (request == "DELETE /api/queue/head/"){
      queue.delete_request();
    }
    else{
      cout << "HTTP/1.1 400 Bad Request" << endl <<
      "Content-Type: application/json; charset=utf-8" << endl <<
      "Content-Length: 0";
    }
  }

  cout << endl;


}