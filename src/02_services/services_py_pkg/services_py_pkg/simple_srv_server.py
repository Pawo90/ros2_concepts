#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts

class SimpleServiceServer(Node):
	def __init__(self):
		super().__init__('simple_service_server')

		# Create a service server
        #
        # Parameters:
        # - Service type: AddTwoInts
        # - Service name: "/add_ints"
        # - Callback function: callbackAddInts (called on every request)
		self.add_ints_service_ = self.create_service(
			AddTwoInts,
			"/add_ints",
			self.callbackAddInts
		)

		self.get_logger().info(
            "Simple Python service server node has been started"
        )

	# Callback function triggered on every received request.
    # Computes the sum of two integers and fills the response.
    #
    # @param request  Contains fields a and b
    # @param response Contains field sum
	def callbackAddInts(self, request: AddTwoInts.Request, response: AddTwoInts.Response):

		self.get_logger().info(f"Received two numbers {request.a} and {request.b}")
		response.sum = request.a + request.b

		return response


def main(args=None):
	rclpy.init(args=args)
	node = SimpleServiceServer()
	
	rclpy.spin(node)
	rclpy.shutdown()

if __name__ == '__main__':
	main()