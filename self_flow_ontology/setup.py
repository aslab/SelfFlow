from setuptools import setup

package_name = 'self_flow_ontology'

setup(
    name=package_name,
    version='0.1.0',
    packages=[package_name],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Jaime de Castro',
    maintainer_email='jaimede.castrod@alumnos.upm.es',
    description='ontology reader for SelfFlow',
    license='GPLv3',
    data_files=[
        ('share/' + package_name, ['package.xml']),
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
	('share/' + package_name + '/owl', ['owl/SelfFlow.owl']),
    ],
    entry_points={
        'console_scripts': [
		'ontology = ' + package_name +'.ontology:main',
        ],
    },
)
