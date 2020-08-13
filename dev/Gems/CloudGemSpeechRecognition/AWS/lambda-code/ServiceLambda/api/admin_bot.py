#
# All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
# its licensors.
#
# For complete copyright and license terms please see the LICENSE at the root of this
# distribution (the "License"). All use of this software is governed by the License,
# or, if provided, by the license below or the license accompanying this file. Do not
# remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#

import service
import lex

@service.api
def put(request, bot_section):
    return {
        'status' : lex.put_bot(bot_section)
    }

@service.api
def get(request, name, version):
    return {
        'bot' : lex.get_bot(name, version)
    }

@service.api
def delete(request, name):
    return {
        'status' : lex.delete_bot(name)
    }

