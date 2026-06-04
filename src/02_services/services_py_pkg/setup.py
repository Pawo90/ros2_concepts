from setuptools import find_packages, setup

package_name = 'services_py_pkg'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='pawo90',
    maintainer_email='pawelp1990@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
            "simple_srv_server = services_py_pkg.simple_srv_server:main",
            "simple_srv_client = services_py_pkg.simple_srv_client:main"
        ],
    },
)
