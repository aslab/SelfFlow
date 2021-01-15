from setuptools import setup

package_name = 'self_flow_ontology'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Jaime de Castro',
    maintainer_email='jaimede.castrod@alumnos.upm.es',
    description='ontology reader fo SelfFlow',
    license='GPLv3',
    entry_points={
        'console_scripts': [
		'onto_reasoner = src.ontology:main'
        ],
    },
)
