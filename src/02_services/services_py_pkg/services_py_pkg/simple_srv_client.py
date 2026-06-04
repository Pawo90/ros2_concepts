#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts


class SimpleServiceClient(Node): 
	def __init__(self):
		super().__init__('simple_service_client')

		# Create a service client
        #
        # Parameters:
        # - Service type: AddTwoInts
        # - Service name: "/add_ints"
		self.client_ = self.create_client(
			AddTwoInts,
			"/add_ints"
		)		

		self.get_logger().info(
            "Simple Python service client node has been started"
        )

    # Sends an async request to the /add_ints service.
    # Waits until the service is available, then sends a and b.
    # Response is handled by callbackAddIntsResponse.
	def callAddInts(self, a: int, b: int):
		while not self.client_.wait_for_service(1.0):
			self.get_logger().warn("Waiting for service...")
		
		request = AddTwoInts.Request()
		request.a = a
		request.b = b

		future = self.client_.call_async(request)
		future.add_done_callback(
			self.callbackAddIntsResponse
		)

    # Callback triggered when the service response is received.
    # Extracts and logs the sum from the response.
	def callbackAddIntsResponse(self, future):
		response = future.result()
		# response: AddTwoInts.Response = future.result()  # hint for IDE
		self.get_logger().info(f"Add ints server respond -> sum is {response.sum}")


def main(args=None):
	rclpy.init(args=args)
	node = SimpleServiceClient()

    # Call - Send request to add 2 + 4
	node.callAddInts(2, 4)

	rclpy.spin(node)
	rclpy.shutdown()

if __name__ == '__main__':
	main()