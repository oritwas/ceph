import ConfigParser
import subprocess
import os
import argparse
import sys

mstart_path = os.getenv('MSTART_PATH')
if mstart_path is None:
    mstart_path = os.path.normpath(os.path.dirname(os.path.realpath(__file__)) + '/../..') + '/'

test_path = os.path.normpath(os.path.dirname(os.path.realpath(__file__))) + '/'

def log(*params):
    s = '>>> '
    for p in params:
        if p:
            s += str(p)

    print s
    sys.stdout.flush()

def mpath(bin, *params):
    s = mstart_path + bin
    for p in params:
        s += ' ' + str(p)

    return s

def tpath(bin, *params):
    s = test_path + bin
    for p in params:
        s += ' ' + str(p)

    return s

def bash(cmd, check_retcode = True):
    log('running cmd: ', cmd)
    process = subprocess.Popen(cmd.split(), stdout=subprocess.PIPE)
    s = process.communicate()[0]
    log('command returned status=', process.returncode, ' stdout=', s)
    if check_retcode:
        assert(process.returncode == 0)
    return (s, process.returncode)

def build(version, cmake):
    if cmake:
        cmd = tpath('cmake_build.sh',version)
    else:
        cmd = tpath('build.sh',version)

    bash(cmd)

def init_region(region, default):
    bash(tpath('test-rgw-call.sh', 'init_region', cluster.cluster_num,
                region, default))

def init_old_zone(zone, default):
    bash(tpath('test-rgw-call.sh', 'init_old_zone', cluster.cluster_num,
               zone))

def create_user(self, user, cluster):
    log('creating user uid=', user.uid)
    cmd = build_cmd('--uid', user.uid, '--display-name', user.display_name,
                    '--access-key', user.access_key, '--secret', user.secret)

    cluster.rgw_admin(' user create ' + cmd)

class RGWConfig:
    def __init__(self, num_clusters):
        self.num_clusters = num_clusters

        self.clusters = {}
        for i in xrange(num_clusters):
            self.clusters[i] = RGWCluster(i + 1)

        self.base_port = 8000

    def setup(self, bootstrap):
        log('bootstapping clusters')
        self.clusters[0].start()
        init_region(self.clusters[0], 'region0', true)
        for i in xrange(1, self.num_clusters):
            self.clusters[i].start()
            init_old_zone(self.clusters[i], 'zone-' + str(i + 1), self.base_port + i, first_zone_port=self.base_port)
        user = RGWUser('tester', '"Test User"', gen_access_key(), gen_secret())
        create_user(user, self.cluster[0])

class RGWBackward:
    def setup(self, old_version, new_version, cmake):
        build(old_version, cmake)
        build(new_version, cmake)
        test()

def init(parse_args):
    cfg = ConfigParser.RawConfigParser({
                                         'old_version': 'master',
                                         'new_version': 'wip-rgw-new-multisite',
                                         'cmake': 'true',
                                         })
    try:
        path = os.environ['RGW_BACKWARD_TEST_CONF']
    except KeyError:
        path = tpath('test_backward.conf')

    try:
        with file(path) as f:
            cfg.readfp(f)
    except:
        print 'WARNING: error reading test config. Path can be set through the RGW_BACKWARD_TEST_CONF env variable'
        pass

    parser = argparse.ArgumentParser(
            description='Run rgw backward compatability tests',
            usage='test_multi [--old-version] [--new-version] [--cmake]')

    section = 'DEFAULT'
    parser.add_argument('--old-version', type=str, default=cfg.get(section, 'old_version'))
    parser.add_argument('--new-version', type=str, default=cfg.get(section, 'new_version'))
    parser.add_argument('--cmake', action='store_true', default=cfg.getboolean(section, 'cmake'))

    argv = []

    if parse_args:
        argv = sys.argv[1:]

    args = parser.parse_args(argv)

    global rgw_backward

    rgw_backward = RGWBackward()
    rgw_backward.setup(args.old_version, args.new_version, args.cmake)

def setup_module():
    init(False)

if __name__ == "__main__":
    init(True)
