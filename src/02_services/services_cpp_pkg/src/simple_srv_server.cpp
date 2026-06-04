#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

using std::placeholders::_1;
using std::placeholders::_2;

class SimpleServiceServer : public rclcpp::Node 
{
public:
	SimpleServiceServer() : Node("simple_service_server") 
	{	
		// Create a service server
		//
		// Parameters:
		// - Service type: AddTwoInts
		// - Service name: "/add_ints"
		// - Callback function: callbackAddInts (called on every request)
		add_ints_service_ = this->create_service<example_interfaces::srv::AddTwoInts>(
			"/add_ints",
			std::bind(&SimpleServiceServer::callbackAddInts, this, _1, _2)
		);

		RCLCPP_INFO(this->get_logger(), "Simple C++ service server node has been started");
	}

private:

	// Callback function triggered on every received request.
	// Computes the sum of two integers and fills the response.
	//
	// @param request  Shared pointer to the request (contains a and b)
	// @param response Shared pointer to the response (contains sum)
	void callbackAddInts(
		const example_interfaces::srv::AddTwoInts::Request::SharedPtr request,
		const example_interfaces::srv::AddTwoInts::Response::SharedPtr response
	)
	{
		RCLCPP_INFO(this->get_logger(),
			"Received two numbers %ld and %ld", request->a, request->b
		);
		response->sum = request->a + request->b;
	}

	// Service server handle for the '/add_ints' service
	rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr add_ints_service_;
};

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);
	auto node = std::make_shared<SimpleServiceServer>();
	 
	rclcpp::spin(node);
	rclcpp::shutdown();
	return 0;
} 