#include "rclcpp/rclcpp.hpp"

class SimpleServiceClient : public rclcpp::Node // MODIFY NAME
{
public:
	SimpleServiceClient() : Node("simple_service_client") // MODIFY NAME
	{
	}
private:
};

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);
	auto node = std::make_shared<SimpleServiceClient>(); // MODIFY NAME
	rclcpp::spin(node);
	rclcpp::shutdown();
	return 0;
} 