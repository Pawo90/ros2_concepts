#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

class SimpleServiceClient : public rclcpp::Node
{
public:
	SimpleServiceClient() : Node("simple_service_client") 
	{	
		// Create a service server
		//
		// Parameters:
		// - Service type: AddTwoInts
		// - Service name: "/add_ints"
		client_ = this->create_client<example_interfaces::srv::AddTwoInts>(
			"/add_ints"
		);
	
		RCLCPP_INFO(this->get_logger(), "Simple C++ service client node has been started");
	}

	// Sends an async request to the /add_ints service.
    // Waits until the service is available, then sends a and b.
    // Response is handled by callbackAddIntsResponse.
	void callAddInts(int a, int b)
	{
		while (! client_->wait_for_service(1s))
		{
			RCLCPP_WARN(this->get_logger(), "Waiting for the server...");
		}

		auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
		request->a = a;
		request->b = b;
		client_->async_send_request(
			request,
			std::bind(&SimpleServiceClient::callbackAddIntsResponse, this, _1)
		);
	}

private:
	// Callback triggered when the service response is received.
    // Extracts and logs the sum from the response.
	void callbackAddIntsResponse(
		rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedFuture future
	)
	{
		auto response = future.get();
		RCLCPP_INFO(this->get_logger(), "Add ints server respond -> sum is %ld", response->sum);
	}

	// Service client handle for the '/add_ints' service
	rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client_;
};

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);
	auto node = std::make_shared<SimpleServiceClient>();

	// Call - Send request to add 2 + 4
	node->callAddInts(2, 8);

	rclcpp::spin(node);
	rclcpp::shutdown();
	return 0;
} 